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
      auto size = egg.getSize();
      auto weight = egg.getWeight();
      for (int i = N; i >= 0; --i) {
        if (i >= (int)size && possible[i - size]) {
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
  static void merge_sort(std::vector<GrainOfSand>::iterator first,
                         std::vector<GrainOfSand>::iterator last) {
    if (last - first <= 1) {
      return;
    }
    auto middle = first + (last - first) / 2;
    merge_sort(first, middle);
    merge_sort(middle, last);
    std::inplace_merge(first, middle, last);
  }

public:
  virtual void arrangeSand(std::vector<GrainOfSand> &grains) {
    auto first = grains.begin(), last = grains.end();
    merge_sort(first, last);
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

  virtual void arrangeSand(std::vector<GrainOfSand> &grains) {
    LonesomeAdventure adventure;
    adventure.arrangeSand(grains);
  }

  virtual Crystal selectBestCrystal(std::vector<Crystal> &crystals) {
    LonesomeAdventure adventure;
    return adventure.selectBestCrystal(crystals);
  }

private:
  uint64_t numberOfShamans;
  ThreadPool councilOfShamans;
};

#endif // SRC_ADVENTURE_H_
