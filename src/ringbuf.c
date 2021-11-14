#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "minmax.h"
#include "ringbuf.h"
#include "util.h"

static int ringbuf_alloc(void **buf_ptr, size_t size)
{
	void *buf;

	if (!is_power_of_two(size))
		return -1;

	buf = malloc(size);
	if (!buf)
		return -1;

	*buf_ptr = buf;
	return 0;
}

int ringbuf_init(struct ringbuf *rb, size_t size)
{
	int ret;

	ret = ringbuf_alloc(&rb->buf, size);
	if (ret < 0)
		return ret;

	rb->size = size;
	rb->mask = size - 1;
	ringbuf_reset(rb);
	return 0;
}

void ringbuf_release(struct ringbuf *rb)
{
	free(rb->buf);
}

void ringbuf_reset(struct ringbuf *rb)
{
	rb->head = 0;
	rb->tail = 0;
}

struct ringbuf *ringbuf_create(size_t size)
{
	int ret;
	struct ringbuf *rb;

	rb = malloc(sizeof(*rb));
	if (rb) {
		ret = ringbuf_init(rb, size);
		if (ret < 0) {
			free(rb);
			return NULL;
		}
	}

	return rb;
}

void ringbuf_destroy(struct ringbuf *rb)
{
	ringbuf_release(rb);
	free(rb);
}

int ringbuf_resize(struct ringbuf *rb, size_t new_size)
{
	int ret;
	size_t count;
	void *new_buf;

	ret = ringbuf_alloc(&new_buf, new_size);
	if (ret < 0)
		return ret;

	count = ringbuf_read(rb, new_buf, new_size);
	free(rb->buf);

	rb->buf = new_buf;
	rb->size = new_size;
	rb->mask = new_size - 1;
	rb->head = count;
	rb->tail = 0;
	return 0;
}

int ringbuf_grow(struct ringbuf *rb)
{
	const size_t new_size = rb->size << 1;

	if (new_size < rb->size)
		return -1;

	return ringbuf_resize(rb, new_size);
}

int ringbuf_shrink(struct ringbuf *rb)
{
	const size_t new_size = rb->size >> 1;

	if (!new_size)
		return -1;

	return ringbuf_resize(rb, new_size);
}

void *ringbuf_memchr(const struct ringbuf *rb, int c)
{
	void *ret;
	size_t count;

	count = ringbuf_count_to_end(rb);
	ret = memchr(ringbuf_tail(rb), c, count);
	if (!ret) {
		count = ringbuf_count(rb) - count;
		ret = memchr(rb->buf, c, count);
	}

	return ret;
}

size_t ringbuf_chrlen(const struct ringbuf *rb, int c)
{
	const char *pos, *tail;

	pos = ringbuf_memchr(rb, c);
	if (!pos)
		return 0;

	tail = ringbuf_tail(rb);
	if (pos >= tail)
		return pos - tail + 1;

	return rb->size + pos - tail + 1;
}

size_t ringbuf_strlen(const struct ringbuf *rb)
{
	return ringbuf_chrlen(rb, 0);
}

size_t ringbuf_read(struct ringbuf *rb, void *buf, size_t bufsize)
{
	size_t to_end;
	char *pbuf = buf;

	bufsize = min(bufsize, ringbuf_count(rb));
	to_end = min(bufsize, ringbuf_count_to_end(rb));
	memcpy(pbuf, ringbuf_tail(rb), to_end);

	if (bufsize > to_end)
		memcpy(pbuf + to_end, rb->buf, bufsize - to_end);

	rb->tail += bufsize;
	return bufsize;
}

size_t ringbuf_read_line(struct ringbuf *rb, void *buf, size_t bufsize)
{
	size_t len;

	len = ringbuf_chrlen(rb, '\n');
	if (len < bufsize)
		bufsize = len;

	return ringbuf_read(rb, buf, bufsize);
}

size_t ringbuf_write(struct ringbuf *rb, const void *buf, size_t bufsize)
{
	size_t to_end;
	const char *pbuf = buf;

	bufsize = min(bufsize, ringbuf_space(rb));
	to_end = min(bufsize, ringbuf_space_to_end(rb));
	memcpy(ringbuf_head(rb), pbuf, to_end);

	if (bufsize > to_end)
		memcpy(rb->buf, pbuf + to_end, bufsize - to_end);

	rb->head += bufsize;
	return bufsize;
}
