#include <iostream>
#include <bitset>
#include <vector>

// Здесь я получаю сырую последовательность битов из вектора.
std::vector<bool> GetBits(std::vector<uint8_t> numbers) {
  std::vector<bool> bits;

  for (uint8_t number : numbers) {
    std::bitset<sizeof(uint8_t) * 8> binary(number);

    for (int i{ sizeof(uint8_t) * 8 - 1 }; i >= 0; --i) {
      bits.push_back(binary[i]);
    }
  }

  return bits;
}

// Сама функция инвертирования битов, получает указатель (итератор) на начало последовательности + смещение
// а также вектор, в котором хранятся номера позиций, где нужно инвертировать бит
void InvertBits(std::vector<bool>::iterator start, size_t deltaBits, std::vector<size_t> bitPositions) {
  std::vector<bool>::iterator end{ start + deltaBits };

  size_t bitPositionIterator{ 0 };
  size_t bitsetIterator{ 0 };

  // Вторым условием здесь проверяю, инвертировали ли мы все биты или нет. Делаю для того, чтобы не было лишних проверок
  // если мы уже инвертировали все биты
  for (std::vector<bool>::iterator ptr{ start }; ptr != end && bitPositionIterator < bitPositions.size(); ++ptr, ++bitsetIterator) {
    if (bitsetIterator == bitPositions[bitPositionIterator]) {
      *ptr = *ptr ^ 1;

      ++bitPositionIterator;
    }
  }
}

int main() {
  std::vector<uint8_t> numbers{ 3, 1, 4, 1 };
  std::vector<size_t> bitPositions;

  size_t bitCount;
  size_t bitPosition;

  std::vector<bool> bits{ GetBits(numbers) };

  std::cout << "How much bits you want to change?: ";
  std::cin >> bitCount;

  for (size_t i{ 0 }; i < bitCount; i++) {
    std::cout << "Enter bit position number " << i + 1 << ": ";
    std::cin >> bitPosition;

    bitPositions.push_back(bitPosition);
  }

  for (const auto& bit : bits) {
    std::cout << bit;
  }
  std::cout << std::endl;

  auto it{ bits.begin() };
  InvertBits(it, 7, bitPositions);

  for (const auto& bit : bits) {
    std::cout << bit;
  }
}