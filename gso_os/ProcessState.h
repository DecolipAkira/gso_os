#pragma once

enum class ProcessState {
	NEW,
	READY,
	RUNNING,
	BLOCKED,
	FINISHED
};