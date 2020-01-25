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

static void merge_sort(size_t a, size_t b, std::vector<GrainOfSand>& grains) {
  if(a >= b)
    return;

  size_t mid = (a+b)/2;
  merge_sort(a, mid, grains);
  merge_sort(mid+1, b, grains); 

  // todo napisanie merge_sorta w miejscu
}

void LonesomeAdventure::arrangeSand(std::vector<GrainOfSand>& grains) {
  size_t N = grains.size();
  merge_sort(0, N-1, grains);
}

Crystal LonesomeAdventure::selectBestCrystal(std::vector<Crystal>& crystals) {
  return *std::max_element(crystals.begin(), crystals.end());
}