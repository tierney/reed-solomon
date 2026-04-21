// SPDX-License-Identifier: GPL-2.0-only

#ifndef _RS_CODEC_H_
#define _RS_CODEC_H_

#include "rslib.h"

namespace cryptogram {

const int kRs255_223ParityBytes = 32;
const int kRs255_223MessageBytes = 223;
const int kRs255_223TotalBytes = 255;
const int kParityArraySize = 32;

// Provides a simple interface for the RS(255,223) reed-solomon error correcting
// code.
class RsCodec {
 public:
  RsCodec();
  virtual ~RsCodec();

  // Non-copyable
  RsCodec(const RsCodec&) = delete;
  RsCodec& operator=(const RsCodec&) = delete;

  int Encode(uint8_t *data, uint16_t *parity);
  int Decode(uint8_t *data, uint16_t *parity);

 private:
  // The memory for an rs_control must be managed explicitly using the ported APIs.
  rs_control *rs_ = nullptr;
};

} // namespace cryptogram

#endif  // _RS_CODEC_H_
