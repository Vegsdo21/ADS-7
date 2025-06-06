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

  // 1. Включим свет в стартовом вагоне, если он выключен
  if (!current->light) {
    current->light = true;
  }

  while (true) {
    // 2. Двигаемся вперёд, пока не встретим вагон с включённым светом
    int steps = 0;
    do {
      current = current->next;
      countOp++;
      steps++;
    } while (!current->light);

    // 3. Выключаем свет в этом вагоне
    current->light = false;

    // 4. Возвращаемся назад на `steps` вагонов
    for (int i = 0; i < steps; ++i) {
      current = current->prev;
      countOp++;
    }

    // 5. Если свет в текущем (стартовом) вагоне выключен — цикл завершён
    if (!current->light)
      return steps;
  }
}

int Train::getOpCount() {
  return countOp;
}
