#include <stdio.h>
#include <stdint.h>

#define MAXSIZE 4096

typedef struct
{
	uint8_t buf[MAXSIZE];
	int head; // dove scrivo
	int tail; // dove leggo
} rbuf_t;

rbuf_t ring;


int push(uint8_t data)
{
	int next = (ring.head + 1) % MAXSIZE;

	/* Circular buffer is full */
	if (next == ring.tail)
		return -1; // quit with error (buffer full)

	ring.buf[ring.head] = data;
	ring.head = next;

	return 0;
}


int pop(uint8_t *data)
{
	/* If the head isn't ahead of the tail, we don't have any data */
	if (ring.head == ring.tail)
		return -1; // quit with error (pop from empty buffer)

	*data = ring.buf[ring.tail];
	ring.buf[ring.tail] = 0; // clear data (optional)

	ring.tail = (ring.tail + 1) % MAXSIZE;

	return 0;
}


void ring_init(void)
{
	ring.head = 0;
	ring.tail = 0;
}


int main(int argc, char *argv[])
{
	int i, ret;
	uint8_t val;

	ring_init();

	if (push(10) < 0) goto error;
	if (push(20) < 0) goto error;
	if (push(50) < 0) goto error;

	for (i=0; i < 3; i++) {
		ret = pop(&val);
		if (ret == 0)
			printf("%d valore inserito: %d\n", i, val);
	}

	return 0;

error:
	return -1;
}
