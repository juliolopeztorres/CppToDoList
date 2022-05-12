#pragma once
#include "RemoveTodoUseCase.h"

using namespace Domain::RemoveTodoUseCase;

RemoveTodoUseCase::RemoveTodoUseCase(RemoveTodoUseCaseRepositoryInterface& repo) : repo(repo) {}

void RemoveTodoUseCase::remove(int id) const {
	this->repo.remove(id);
}
