#include "adventure.h"


uint64_t LonesomeAdventure::packEggs(std::vector<Egg> eggs, BottomlessBag& bag) {
  // todo dopisac odzyskiwanie wyniku
  int N = bag.getCapacity();
  std::vector<uint64_t> val(N + 1, UINT64_MAX);
  val[0] = 0;
  for(auto &egg : eggs) {
    auto size = egg.getSize();
    auto weight = egg.getWeight();
    for(int i = N; i >= 0; --i) {
      if(val[i - size] + weight < val[i]) {
        val[i] = val[i - size] + weight;
      }
    }
  }
  uint64_t ret = 0;
  for(auto& c : val) {
    if(c != UINT64_MAX)
      ret = std::max(ret, c);
  }
  return ret;
}

static void merge_sort(std::vector<GrainOfSand>::iterator first, std::vector<GrainOfSand>::iterator last) {
	if (last - first <= 1) {
		return;
	}
	auto middle = first + (last - first) / 2;
	merge_sort(first, middle);
	merge_sort(middle, last);
	std::inplace_merge(first, middle, last);
}

void LonesomeAdventure::arrangeSand(std::vector<GrainOfSand>& grains) {
  auto first = grains.begin(), last = grains.end();
  merge_sort(first, last);
}

Crystal LonesomeAdventure::selectBestCrystal(std::vector<Crystal>& crystals) {
  return *std::max_element(crystals.begin(), crystals.end());
}