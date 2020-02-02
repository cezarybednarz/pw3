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

 private:
  void quick_sort(std::vector<GrainOfSand>::iterator first,
                         std::vector<GrainOfSand>::iterator last) {
    if (last - first <= 1) {
      return;
    }
    std::vector<GrainOfSand>::iterator mid = first + (last - first) / 2;
    std::nth_element(first, mid, last);
    auto r = last - 1;
    for(auto it = first; it < mid; it++) {
      if(*mid < *it) {
        while(r > mid && *mid < *r) {
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
    LonesomeAdventure adventure;
    return adventure.packEggs(eggs, bag);
  }

 private:
  void quick_sort(std::vector<GrainOfSand>::iterator first,
                  std::vector<GrainOfSand>::iterator last) {
    if (last - first <= 1) {
      return;
    }
    std::vector<GrainOfSand>::iterator mid = first + (last - first) / 2;
    std::nth_element(first, mid, last);
    auto r = last - 1;
    for(auto it = first; it < mid; it++) {
      if(*mid < *it) {
        while(r > mid && *mid < *r) {
          r--;
        }
        std::iter_swap(it, r);
      }
    }
    std::future<void> f1 = councilOfShamans.enqueue([first, mid, this] {quick_sort(first, mid);});
    std::future<void> f2 = councilOfShamans.enqueue([mid, last, this] {quick_sort(mid, last);});
    f1.get();
    f2.get();
  }

  virtual void arrangeSand(std::vector<GrainOfSand> &grains) {
    auto first = grains.begin(), last = grains.end();
    quick_sort(first, last);
  }

  virtual Crystal selectBestCrystal(std::vector<Crystal> &crystals) {
    Crystal result;
    std::vector<std::future<Crystal>> results;

    size_t interval = crystals.size() / numberOfShamans + 1;
    size_t counter = 0;
    auto curr_first = crystals.begin(), curr_last = crystals.begin();

    for(;;) {

      if(curr_last == crystals.end() || counter == interval) {
        results.emplace_back(councilOfShamans.enqueue([curr_first, curr_last] {
          return *std::max_element(curr_first, curr_last);
        }));

        curr_first = curr_last;
        counter = 0;

        if(curr_last == crystals.end()) {
          break;
        }
      }

      curr_last++;
      counter++;
    }

    for(auto&& r: results) {
      result = std::max(r.get(), result);
    }

    return result;
  }

 private:
  uint64_t numberOfShamans;
  ThreadPool councilOfShamans;
};

#endif  // SRC_ADVENTURE_H_
