#include "hw06.h"
#include <cmath>
#include <iostream>

float distance(const linalg::Vector &x, const linalg::Vector &y) {
  return linalg::norm(y - x);
}

linalg::Vector normalize_to_range(const linalg::Vector &x) {
  auto xmin{linalg::min(x)};
  auto xmax{linalg::max(x)};
  return (x - xmin) / (xmax - xmin);
}

int main() {
  const linalg::Vector x({0.43278453f, 0.14044682f, 0.83455662f, 0.67914679f,
                          0.58428674f, 0.89063629f, 0.50002398f, 0.45118024f,
                          0.31165657f, 0.74530963f});
  const linalg::Vector y({0.7733542f, 0.15135689f, 0.60560901f, 0.13599972f,
                          0.54029262f, 0.06325417f, 0.76008249f, 0.02780873f,
                          0.70149423f, 0.3950426f});
  const linalg::Vector z({1.20613873f, 0.29180371f, 1.44016563f, 0.81514651f,
                          1.12457936f, 0.95389046f, 1.26010647f, 0.47898897f,
                          1.0131508f, 1.14035223f});

  std::cout << "Given a vector x: " << x << "\n";
  std::cout << "And a vector y: " << y << "\n";
  std::cout << "The distance between them is: " << distance(x, y) << "\n";

  std::cout << "\nLet's do some more math:\n";

  const auto w{((x * linalg::max(z)) + 5.f) / 3.f};
  const auto v{y * linalg::min(z)};

  const auto floored{linalg::floor(w)};
  const auto ceiled{linalg::floor(w)};

  std::cout << "w: " << w << "\n";
  std::cout << "floor(w): " << linalg::floor(w) << "\n";
  std::cout << "ceil(w): " << linalg::ceil(w) << "\n\n";
  std::cout << "v: " << v << "\n";
  std::cout << "norm(v): " << linalg::norm(v) << "\n";
  std::cout << "normalized(v): " << linalg::normalized(v) << "\n";
  std::cout << "norm(normalized(v)): " << linalg::norm(linalg::normalized(v))
            << "\n\n";

  std::cout << "dot(v, v): " << std::sqrt(linalg::dot(v, v)) << "\n";
  std::cout << "norm(v): " << linalg::norm(v) << "\n";
  std::cout << "dot(v, w): " << linalg::dot(v, w) << "\n\n";

  std::cout << "Normalizing w to the range [0, 1]:\n";
  std::cout << "w: " << w << "\n";
  auto w_normed_to_range{normalize_to_range(w)};
  std::cout << "w normalized to [0, 1]: " << w_normed_to_range << "\n";
  std::cout << "Euclidean norm of w normalized to [0, 1]: "
            << linalg::norm(w_normed_to_range) << "\n";
}
