#pragma once
#include "EditTodoUseCase.h"

using namespace Domain::EditTodoUseCase;

EditTodoUseCase::EditTodoUseCase(EditTodoUseCaseRepositoryInterface& repo) : repo(repo) {}

void EditTodoUseCase::edit(const Task& task) const
{
	this->repo.edit(task);
}
