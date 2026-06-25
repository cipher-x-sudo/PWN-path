# Codex Workspace Instructions

## Handoffs

- When the user asks for a handoff, continuation note, restart summary, next-agent brief, status transfer, or asks what the next Codex session should know, use `$handoff`.
- For substantial work that is paused, interrupted, or likely to continue in a future session, offer or prepare a concise handoff before stopping.
- Keep handoffs actionable: include the goal, current state, important context, next steps, and risks or unknowns.
- Mention commands run, test results, relevant file paths, and any dirty working tree state when known.

## User Learning Style

- Keep pwn/debugging explanations short, direct, and practical.
- Avoid extra theory unless the user asks for it.
- Explain assembly and memory in small chunks: instruction, meaning, why it matters.
- Prefer guiding questions and logic over giving full challenge answers.

## Lab Creation Rules

- When creating a new lab, copy `templates/exploit.py` into the lab as the starter exploit.
- Do not write the final exploit chain into the delivered starter exploit.
- Leave clear TODOs or placeholders for the user to fill in.
- If verification needs a solved exploit, test it privately with a temporary script or command that is not saved in the repo.
- The delivered lab should contain the challenge, build files, README hints, and an editable template-based exploit, not the completed solution.
