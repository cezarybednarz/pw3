#ifndef SRC_ADVENTURE_H_
#define SRC_ADVENTURE_H_

#include <algorithm>
#include <vector>

#include "../third_party/threadpool/threadpool.h"

#include "types.h"
#include "utils.h"

class Adventure {
 public:
  virtual ~Adventure() = default;

  virtual uint64_t packEggs(std::vector<Egg> eggs, BottomlessBag &bag) = 0;

  virtual void arrangeSand(std::vector<GrainOfSand> &grains) = 0;

  virtual Crystal selectBestCrystal(std::vector<Crystal> &crystals) = 0;
};

class LonesomeAdventure : public Adventure {
 public:
  LonesomeAdventure() {}

  virtual uint64_t packEggs(std::vector<Egg> eggs, BottomlessBag &bag) {
    int N = bag.getCapacity();

    std::vector<uint64_t> DP(N + 1, 0);
    std::vector<bool> possible(N + 1, false);
    std::vector<std::pair<uint64_t, uint64_t>> retrieve(N + 1,
                                                        std::make_pair(0, 0));
    possible[0] = true;

    for (auto &egg : eggs) {
      int size = egg.getSize();
      auto weight = egg.getWeight();
      for (int i = N; i >= 0; --i) {
        if (i >= size && possible[i - size]) {
          if (DP[i - size] + weight > DP[i]) {
            DP[i] = DP[i - size] + weight;
            retrieve[i] = {size, weight};
            possible[i] = true;
          }
        }
      }
    }

    for (int i = N; i >= 0; --i) {
      if (possible[i]) {
        int curr = i;
        while (curr > 0) {
          bag.addEgg(Egg(retrieve[curr].first, retrieve[curr].second));
          curr -= retrieve[i].first;
        }
        return DP[i];
      }
    }

    return 0;
  }

  static void quick_sort(std::vector<GrainOfSand>::iterator first,
                         std::vector<GrainOfSand>::iterator last) {
    if (last - first <= 1) {
      return;
    }
    std::vector<GrainOfSand>::iterator mid = first + (last - first) / 2;
    std::nth_element(first, mid, last);
    auto r = last - 1;
    for (auto it = first; it < mid; it++) {
      if (*mid < *it) {
        while (r > mid && *mid < *r) {
          r--;
        }
        std::iter_swap(it, r);
      }
    }
    quick_sort(first, mid);
    quick_sort(mid, last);
  }

 public:
  virtual void arrangeSand(std::vector<GrainOfSand> &grains) {
    auto first = grains.begin(), last = grains.end();
    quick_sort(first, last);
  }

  virtual Crystal selectBestCrystal(std::vector<Crystal> &crystals) {
    return *std::max_element(crystals.begin(), crystals.end());
  }
};


class TeamAdventure : public Adventure {
 public:
  explicit TeamAdventure(uint64_t numberOfShamansArg)
      : numberOfShamans(numberOfShamansArg),
        councilOfShamans(numberOfShamansArg) {}

  uint64_t packEggs(std::vector<Egg> eggs, BottomlessBag &bag) {
    const uint64_t threshold = 20;

    uint64_t N = bag.getCapacity();
    uint64_t M = eggs.size();

    std::vector<std::vector<uint64_t>> DP(M + 1,
                                          std::vector<uint64_t>(N + 1, 0));
    std::vector<std::vector<bool>> possible(M + 1,
                                            std::vector<bool>(N + 1, false));
    std::vector<std::pair<uint64_t, uint64_t>> retrieve(N + 1,
        std::make_pair(0, 0));

    possible[0][0] = true;

    for (size_t i = 1; i <= M; i++) {
      uint64_t size = eggs[i - 1].getSize();
      uint64_t weight = eggs[i - 1].getWeight();

      uint64_t interval = std::max(N / numberOfShamans + 1, threshold);


      std::vector<std::future<void>> results;
      for (size_t first = 0; first <= N; first += interval) {
        results.emplace_back(councilOfShamans.enqueue(
            [first, &DP, N, size, weight, &possible, &retrieve, interval, i] {
          for (size_t j = first; j <= std::min(N, first + interval - 1); j++) {
            if (possible[i - 1][j]) {
              DP[i][j] = DP[i - 1][j];
              possible[i][j] = true;
            }

            if (j >= size && possible[i - 1][j - size]) {
              possible[i][j] = true;
              if (DP[i][j] < DP[i - 1][j - size] + weight) {
                DP[i][j] = DP[i - 1][j - size] + weight;
                retrieve[j] = {size, weight};
              }
            }
          }
        }));
      }

      for (auto&& result : results) {
        result.get();
      }
    }

    for (int i = N; i >= 0; --i) {
      if (possible[M][i]) {
        int curr = i;
        while (curr > 0) {
          bag.addEgg(Egg(retrieve[curr].first, retrieve[curr].second));
          curr -= retrieve[i].first;
        }
        return DP[M][i];
      }
    }

    return 0;
  }


 public:
  void quick_sort(std::vector<GrainOfSand>::iterator first,
       std::vector<GrainOfSand>::iterator last, int threshold) {
     if (last - first <= threshold) {
      std::sort(first, last);
      return;
    }

    std::vector<GrainOfSand>::iterator mid = first + (last - first) / 2;
    std::nth_element(first, mid, last);
    auto r = last - 1;
    for (auto it = first; it < mid; it++) {
      if (*mid < *it) {
        while (r > mid && *mid < *r) {
          r--;
        }
        std::iter_swap(it, r);
      }
    }
    auto f = councilOfShamans.enqueue([first, mid, threshold, this] {
     quick_sort(first, mid, threshold);
    });
    quick_sort(mid, last, threshold);
    f.get();
  }

  virtual void arrangeSand(std::vector<GrainOfSand> &grains) {
    auto first = grains.begin(), last = grains.end();
    quick_sort(first, last, (last - first) / numberOfShamans + 1);
  }

  virtual Crystal selectBestCrystal(std::vector<Crystal> &crystals) {
    Crystal result;
    std::vector<std::future<Crystal>> results;

    size_t interval = crystals.size() / numberOfShamans + 1;
    size_t counter = 0;
    auto curr_first = crystals.begin(), curr_last = crystals.begin();

    for (;;) {
      if (curr_last == crystals.end() || counter == interval) {
        results.emplace_back(councilOfShamans.enqueue([curr_first, curr_last] {
          return *std::max_element(curr_first, curr_last);
        }));

        curr_first = curr_last;
        counter = 0;

        if (curr_last == crystals.end()) {
          break;
        }
      }

      curr_last++;
      counter++;
    }

    for (auto&& r : results) {
      result = std::max(r.get(), result);
    }

    return result;
  }

 private:
  uint64_t numberOfShamans;
  ThreadPool councilOfShamans;
};

#endif  // SRC_ADVENTURE_H_
