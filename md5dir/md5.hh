#ifndef _MD5_H
#define _MD5_H 1

#define MD5_DIGEST_SIZE 16
#define MD5_BLOCK_SIZE 64

#ifndef __THROW
#define __THROW       throw ()
#endif

#include <array>
#include <cstdint>
#include <string.h>
#include <iomanip>

namespace hash_ns {
/* Structure to save state of computation between the single steps.  */
  using std::array;  
  using boost::filesystem::path;
  using std::string;
struct md5_ctx
{
  uint32_t A;
  uint32_t B;
  uint32_t C;
  uint32_t D;

  uint32_t total[2];
  uint32_t buflen;     /* ≥ 0, ≤ 128 */
  uint32_t buffer[32]; /* 128 bytes; the first buflen bytes are in use */
};

/*
 * The following three functions are build up the low level used in
 * the functions 'md5_stream' and 'md5_buffer'.
 */

/* Initialize structure containing state of computation.
   (RFC 1321, 3.3: Step 3)  */
extern void md5_init_ctx (struct md5_ctx *ctx) __THROW;

/* Starting with the result of former calls of this function (or the
   initialization function update the context for the next LEN bytes
   starting at BUFFER.
   It is necessary that LEN is a multiple of 64!!! */
extern void md5_process_block (const void *buffer, size_t len,
                                 struct md5_ctx *ctx) __THROW;

/* Starting with the result of former calls of this function (or the
   initialization function update the context for the next LEN bytes
   starting at BUFFER.
   It is NOT required that LEN is a multiple of 64.  */
extern void md5_process_bytes (const void *buffer, size_t len,
                                 struct md5_ctx *ctx) __THROW;

/* Process the remaining bytes in the buffer and put result from CTX
   in first 16 bytes following RESBUF.  The result is always in little
   endian byte order, so that a byte-wise output yields to the wanted
   ASCII representation of the message digest.  */
extern void *md5_finish_ctx (struct md5_ctx *ctx, void *resbuf) __THROW;


/* Put result from CTX in first 16 bytes following RESBUF.  The result is
   always in little endian byte order, so that a byte-wise output yields
   to the wanted ASCII representation of the message digest.  */
extern void *md5_read_ctx (const struct md5_ctx *ctx, void *resbuf) __THROW;


/* Compute MD5 message digest for LEN bytes beginning at BUFFER.  The
   result is always in little endian byte order, so that a byte-wise
   output yields to the wanted ASCII representation of the message
   digest.  */
extern void *md5_buffer (const char *buffer, size_t len,
                           void *resblock) __THROW;

}
#endif
