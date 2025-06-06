// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() {
  countOp = 0;
  first = nullptr;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    newCar->next = newCar;
    newCar->prev = newCar;
  } else {
    Car* tail = first->prev;
    newCar->next = first;
    newCar->prev = tail;
    tail->next = newCar;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (!first) return 0;

  Car* current = first;
  countOp = 0;

  if (!current->light) {
    current->light = true;
  }

  while (true) {
    int steps = 0;
    do {
      current = current->next;
      countOp++;
      steps++;
    } while (!current->light);

    current->light = false;


    for (int i = 0; i < steps; ++i) {
      current = current->prev;
      countOp++;
    }


    if (!current->light)
      return steps;
  }
}

int Train::getOpCount() {
  return countOp;
}
