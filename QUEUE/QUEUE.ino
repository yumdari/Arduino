#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int head, tail; // 큐의 head와 tail index를 뜻하는 int형 변수 head와 tail: 전역변수이기 때문에 자동으로 0으로 초기화
int queue[1000]; // 배열 기반 큐를 구현하기 위한 큐 배열

void push_array(int value) { // 배열 기반 큐 삽입 함수(queue 배열에 value를 넣어주는 함수)
  if (tail == 1000) { // 큐가 가득 찬 상태(오버플로우) // tail = -1이라면 top == 999
    printf("큐 오버플로우 발생\n");
    return;
  }
  else { // 큐가 가득 차지 않은 상태
    queue[tail++] = value; // 큐의 tail에 value를 삽입하고 tail 값 1 증가 // circular queue일 때 [head++ % 배열 크기]
  }
}

int pop_array(void) { // 배열 기반 큐 삭제 함수
  if (head == tail) { // 큐가 비어 있는 상태(언더플로우)
    printf("큐 언더플로우 발생.\n");
    return -1;
  }
  else { // 큐가 비어 있지 않은 상태
    return queue[head++]; // 큐의 head 값 1 증가 후 return(큐의 head에서 값 삭제) // circular queue일 때 [head++ % 배열 크기]
  }
}

void show_array(void) { // 배열 기반 큐 출력 함수
  if (head == tail) { // 큐가 비어있는 상태
    printf("큐가 비어있습니다.\n");
    return;
  }
  else { // 큐가 비어 있지 않은 상태
    for (int i = head; i < tail; i++) { // 큐 전체를 탐색
      printf("%d ", queue[i]); // 큐의 각 index 출력
    }
  }
  printf("\n");
}

int main(void) {
  push_array(3);
  show_array();
  push_array(7);
  show_array();
  push_array(2);
  show_array();
  pop_array();
  show_array();
  pop_array();
  show_array();
  pop_array();
  show_array();
  return 0;
}
[출처] 배열 기반 큐|작성자 이하로
