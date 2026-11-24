// Debuggee fixture for exercising gf2's debugger features.
// Build: gcc -g -O0 -fno-omit-frame-pointer -o debuggee debuggee.c -lpthread
//
// Scenarios covered:
//   - step over / step in / step out across nested calls
//   - breakpoints on source lines and addresses
//   - locals, watch expressions, pointers, arrays, structs
//   - multi-frame backtrace (stack window)
//   - threads (thread window)
//   - disassembly view (ASM window)
//   - function pointer calls (function-name detection)
//   - data breakpoints / watchpoints
//   - inspecting struct layouts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

struct Point {
	int x;
	int y;
};

struct Packet {
	int id;
	struct Point position;
	double values[4];
	char label[32];
	struct Packet *next;
};

struct Packet globalPacket = {
	.id = 100,
	.position = { .x = 3, .y = 7 },
	.values = { 1.5, 2.5, 3.5, 4.5 },
	.label = "global-packet",
	.next = NULL,
};

int globalCounter = 0;

// Recursive function for deep call stacks and step-out tests.
int fibonacci(int n) {
	if (n <= 1) return n;
	int left = fibonacci(n - 1);
	int right = fibonacci(n - 2);
	return left + right;
}

// Nested calls for step over/into/out.
int add(int a, int b) {
	int result = a + b;
	globalCounter++;
	return result;
}

int multiply(int a, int b) {
	int result = 0;
	for (int i = 0; i < b; i++) {
		result = add(result, a);
	}
	return result;
}

// Function pointer call — tests gf2's backward scan for function names.
typedef int (*BinaryOp)(int, int);

int applyOperation(BinaryOp operation, int a, int b) {
	return operation(a, b);
}

// Struct manipulation for the Struct and Watch windows.
void fillPacket(struct Packet *packet, int id) {
	packet->id = id;
	packet->position.x = id * 2;
	packet->position.y = id * 3;
	for (int i = 0; i < 4; i++) {
		packet->values[i] = i + 0.25;
	}
	snprintf(packet->label, sizeof(packet->label), "packet-%d", id);
	packet->next = NULL;
}

void *workerThread(void *argument) {
	int iterations = *(int *) argument;
	int localSum = 0;
	for (int i = 0; i < iterations; i++) {
		localSum += i;
		globalCounter++;
	}
	return (void *) (intptr_t) localSum;
}

int main(void) {
	printf("debuggee: starting\n");

	int localA = 10;
	int localB = 3;
	int sum = add(localA, localB);
	int product = multiply(localA, localB);
	int fib = fibonacci(8);

	BinaryOp operation = add;
	int viaPointer = applyOperation(operation, localA, localB);

	struct Packet localPacket;
	fillPacket(&localPacket, 42);

	int threadIterations = 1000000;
	pthread_t thread;
	pthread_create(&thread, NULL, workerThread, &threadIterations);

	// Watchpoint candidate: modify a heap location repeatedly.
	int *heapValue = (int *) malloc(sizeof(int));
	*heapValue = 1;
	for (int i = 0; i < 5; i++) {
		*heapValue += i;
	}

	pthread_join(thread, NULL);
	free(heapValue);

	printf("sum=%d product=%d fib=%d viaPointer=%d counter=%d\n",
			sum, product, fib, viaPointer, globalCounter);
	printf("packet id=%d pos=(%d,%d) label=%s\n",
			localPacket.id, localPacket.position.x, localPacket.position.y, localPacket.label);
	printf("debuggee: done\n");
	return 0;
}
