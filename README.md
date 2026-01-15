*This project has been created as part of the 42 curriculum by frmanett.*

# get_next_line

**Description**
- **Project goal:** Implement `get_next_line()`, a function that reads from a file
	descriptor and returns the next line ending with a newline (`\n`) or EOF.
- **Overview:** The function repeatedly reads from a file descriptor using a
	fixed-size buffer (`BUFFER_SIZE`), concatenates data until a newline is
	encountered (or EOF), and returns the line as a malloc'd string. The project
	includes utility helpers and a bonus variant that supports reading from
	multiple file descriptors concurrently.

**Instructions**
- **Build (example):** compile the sources with a C compiler. Example using
	`cc`:

	```bash
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=32 \
		get_next_line.c get_next_line_utils.c main.c -o gnl
	```

- **Files of interest:**
	- `get_next_line.c`, `get_next_line_bonus.c`
	- `get_next_line_utils.c`, `get_next_line_utils_bonus.c`

**Algorithm explanation and justification**
- **High-level approach:**
	1. Maintain a persistent remainder (also called "stash") per file descriptor
		 that stores data read but not yet returned to the caller.
	2. On each `get_next_line()` call, check the remainder for a newline. If
		 present, extract the next line and update the remainder.
	3. If no newline is found, `read()` from the fd into a temporary buffer of
		 size `BUFFER_SIZE`, append it to the remainder, and repeat until a newline
		 appears or `read()` returns 0 (EOF).
	4. When a newline or EOF is reached, allocate and return a string containing
		 the next line (including the trailing `\n` when present), and update the
		 remainder to hold any leftover bytes for future calls.

- **Why this algorithm:**
	- **Efficiency:** Using a moderate `BUFFER_SIZE` reduces the number of
		`read()` syscalls while keeping memory usage low. The algorithm processes
		each byte at most a small constant number of times (append, scan for
		newline, extract), so overall time is O(n) for n bytes read.
	- **Correctness:** Keeping a remainder between calls preserves bytes beyond
		the returned line, which is necessary when a single `read()` reads more
		than one line or a partial line. Returning exactly one line per call
		matches the subject requirements.
	- **Multiple file descriptors (bonus):** For supporting multiple fds
		concurrently, maintain a separate remainder per fd (commonly implemented
		with an array indexed by fd or a small linked list keyed by fd). This
		prevents cross-mixing of data when reading from different descriptors.
	- **Memory considerations:** Each returned line is `malloc`ed and must be
		freed by the caller. The remainder grows at most by `BUFFER_SIZE` per
		successful `read()` and is trimmed when lines are extracted.

- **Edge cases handled:**
	- Files that don't end with a newline (return last line on EOF).
	- Empty files (returns NULL immediately).
	- Very long lines (works by repeated reads; only limited by available
		memory for the returned line).

**Resources**
- **POSIX & C references:**
	- `read(3)` and man pages for your platform (e.g., `man 3 read`).
	- ISO C standard string and memory functions (`malloc`, `free`).
- **Guides:**
	- The 42 subject description and peer notes (internal resources at 42).
	- 42's helpers.
	- Sfabi28's tester.

- **How AI was used:** AI was used to refine this `README.md` and to help formulate
	a clear algorithm explanation. AI suggestions were limited to documentation and
	did not change core project source code files.
