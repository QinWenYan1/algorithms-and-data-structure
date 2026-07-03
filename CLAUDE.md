# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a personal study-notes repository for data structures and algorithms, following the [代码随想录](https://programmercarl.com/) curriculum. All content is in Chinese. There is no build system, test framework, or compilable source code — the repo consists entirely of Markdown notes with embedded C++ code blocks.

## Content Organization

All problem notes live under `代码随想录题目/`, organized by topic subdirectory:

| Directory | Topic |
|---|---|
| `array_vector/` | Array / Vector |
| `hash_table/` | Hash Table |
| `linked_list/` | Linked List |
| `stack_queue/` | Stack & Queue |
| `string/` | String |
| `dynamic_programming/` | Dynamic Programming |
| `binary_tree/` | Binary Tree |
| `double_ptr/` | Two-Pointer |

Each subdirectory has its own `README.md` serving as chapter navigation. Incomplete chapters: Binary Tree, DP, Backtracking (not started), Graph Theory (not started).

## File Naming Convention

Problem files follow the pattern: `{topic}_{number}_{english_name}.md`

Examples: `arr_vec_1_binary_search.md`, `linked_list_1_remove_elements.md`, `dp_1_fibonacci.md`

## Adding a New Problem Note

When asked to generate a note for a new LeetCode problem, use the 6-module template defined in the README:

1. **核心思路** — bold-named approach + 3–5 lines explaining the data structure choice, key actions, and why
2. **关键点** — 3–4 numbered, bold-titled points covering mechanisms, edge cases/counterexamples, and code correspondence
3. **复杂度分析** — markdown table (指标/复杂度/说明) with explanations of what drives the complexity
4. **易错提醒** — 2–3 `⚠️` items covering code-level errors that cause WA/RE/TLE
5. **记忆口诀** — optional one-line mnemonic rhyme
6. **代码** — the C++ solution with stage comments (`// 阶段1: …`), intent comments (`// 为什么…`), and boundary warnings (`// ⚠️ …`)

Refer to existing files like `array_vector/arr_vec_1_binary_search.md` for the file header format (LeetCode link, difficulty, reference links). The note body currently varies in template adherence — new notes should follow the full 6-module structure.

## Language & Tooling

- All code examples are C++ (C++17). VS Code settings in `.vscode/settings.json` associate standard library headers with the `cpp` language mode.
- No build system, tests, or linting exist. To verify C++ code compiles, paste it into a LeetCode submission or a local `main.cpp` and compile with `g++ -std=c++17 -Wall -Wextra`.
