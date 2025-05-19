#ifndef FLOAT16_FLOAT16_H
#define FLOAT16_FLOAT16_H

#include <cstdint>

/**
 * @brief 16bitのfloat型のクラス
 * @details floatやdoubleなどと同様に扱うことができる。
 *          精度は落ちるので注意すること。
 *          有効桁数は10進数で約3桁、2進数で11bit(0~2047)
 */
class float16 {
 private:
  int16_t data_;

  int16_t FloatCompress(float float32_value) const {
    if (float32_value == 0) return 0;
    int32_t data_f = *reinterpret_cast<int32_t*>(&float32_value);
    int16_t sign = data_f >> 16 & 0b1 << 15;
    int16_t exp = (((data_f >> 23) - 127 + 15) & 0x1f) << 10;
    int16_t frac = (data_f >> (23 - 10)) & 0x3ff;

    // 数値の絶対値が大きすぎるときは最大値に符号をつけて返す
    if (((data_f & (~(0b1 << 31))) >> 23) - 127 > 15)
      return sign | 0b111111111111111;
    // 数値が0に近すぎる時は0を返す
    else if (((data_f & (~(0b1 << 31))) >> 23) - 127 < -14)
      return 0;

    return sign | exp | frac;
  }

  float FloatDecompress(int16_t float16_data) const {
    if (float16_data == 0) return 0;
    int32_t sign = (float16_data & 0b1 << 15) << 16;
    int32_t exp = ((((float16_data >> 10) & 0x1f) - 15 + 127) & 0xff) << 23;
    int32_t frac = (float16_data & 0x3ff) << (23 - 10);
    int32_t data_f = sign | exp | frac;
    return *reinterpret_cast<float*>(&data_f);
  }

 public:
  float16() = default;
  explicit(false) float16(float float32_value)  // NO_LINT
      : data_(FloatCompress(float32_value)) {}
  operator float() const { return FloatDecompress(data_); }
  //
  float16 operator+(const float16& other) const {
    return float16(static_cast<float>(*this) + static_cast<float>(other));
  }

  float16 operator-(const float16& other) const {
    return float16(static_cast<float>(*this) - static_cast<float>(other));
  }

  float16 operator*(const float16& other) const {
    return float16(static_cast<float>(*this) * static_cast<float>(other));
  }

  float16 operator/(const float16& other) const {
    return float16(static_cast<float>(*this) / static_cast<float>(other));
  }

  //
  float16& operator+=(const float16& other) {
    *this = *this + other;
    return *this;
  }

  float16& operator-=(const float16& other) {
    *this = *this - other;
    return *this;
  }

  float16& operator*=(const float16& other) {
    *this = *this * other;
    return *this;
  }

  float16& operator/=(const float16& other) {
    *this = *this / other;
    return *this;
  }

  //
  bool operator==(const float16& other) const {
    return static_cast<float>(*this) == static_cast<float>(other);
  }

  bool operator!=(const float16& other) const { return !(*this == other); }

  bool operator<(const float16& other) const {
    return static_cast<float>(*this) < static_cast<float>(other);
  }

  bool operator>(const float16& other) const {
    return static_cast<float>(*this) > static_cast<float>(other);
  }

  bool operator<=(const float16& other) const { return !(*this > other); }

  bool operator>=(const float16& other) const { return !(*this < other); }
};

#endif  // FLOAT16_FLOAT16_H