/**
 * 
 *  [] 
 *  [this]
 *  [x, &y]   x by value, y by reference
 *  [&]       all by reference
 *  [=]       all by implicit value
 *  [&, x]    x by value, others by reference
 *  [=,&z]    z by reference, others by implicit value
 */

std::vector<int> cononical{1,2,3,4,5};
int total = 0, val= 6;
std::for_each(begin(cononical), end(cononical), [&, val, this](int x) {
  total += x * val * this->func()
} 

auto lame = [](int x){return x * x;};   // okay
/**
 * -> return type
 */
auto lame = [](int x) -> int {return x * x;}

int lambaste = 100;
auto lamebrain = [=](int x){return lambaste * x;}; // use lambaste outside
auto lamebrain = [&](int x){return lambaste * x;}; // use reference of lambaste outside