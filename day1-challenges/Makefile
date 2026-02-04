# Build all Day 1 challenge binaries (all 64-bit; no multilib required).
.PHONY: all clean

all:
	@for d in challenge_*/; do \
		echo "== $$d =="; \
		(cd "$$d" && make); \
	done

clean:
	@for d in challenge_*/; do (cd "$$d" && make clean); done
