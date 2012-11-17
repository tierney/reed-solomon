#include <cstdlib>
#include <ctime>
#include <iostream>
#include "rslib.h"

void printf_data(uint8_t *data, size_t len) {
  for (int i = 0; i < len; i++) {
    std::cout << (int)data[i];
  }
  std::cout << std::endl;
}

const int kParityLen = 16;

int main(int argc, char** argv) {
  srand(time(NULL));

  rs_control *rs = init_rs(8, 0x187, 0, 1, 16);

  /* Parity buffer. Size = number of roots */
  uint16_t par[kParityLen];
  /* Initialize the parity buffer */
  memset(par, 0, sizeof(par));
  /* Encode 32 byte in data8. Store parity in buffer par */
  uint8_t orig_copy[223];
  uint8_t  data[223];
  for (int i = 0; i < 223; i++) {
    memset(data + i, 1, 1);
  }
  std::cout << "Original data:" << std::endl;
  printf_data(data, 223);
  memmove(orig_copy, data, 223);

  {
  int nerrors = 0;
  for (int i = 0; i < 223; i++) {
    if (orig_copy[i] != data[i]) {
      nerrors++;
    }
  }
  std::cout << "Differences: " << nerrors << std::endl;;
  }

  encode_rs8 (rs, data, 223, par, 0);
  std::cout << "Encoded data:" << std::endl;
  std::cout << "Parity: " << std::endl;

  printf_data(data, 223);
  {
    for (int i = 0; i < kParityLen; i++) {
      std::cout << par[i] << " ";
    }
    std::cout << std::endl;
  }

  int nchanges = 0;
  for (int i = 0; i < 223; i++) {
    if (rand() % 15 == 0) {
      memset(data + i, rand() % 255, 1);
      nchanges++;
    }
  }
  std::cout << "Sent data (" << nchanges << " changes) : " << std::endl;
  printf_data(data, 223);

  int numerr = decode_rs8(rs, data, par, 223, NULL, 0, NULL, 0, NULL);
  std::cout << "Num errors: " << numerr << std::endl;
  std::cout << "Decoded data:" << std::endl;
  printf_data(data, 223);

  {
  int nerrors = 0;
  for (int i = 0; i < 223; i++) {
    if (orig_copy[i] != data[i]) {
      nerrors++;
    }
  }
  std::cout << "Differences: " << nerrors;
  }

  free_rs(rs);

  return 0;
}
