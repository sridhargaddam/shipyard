include Makefile.inc

TARGETS := $(shell ls -p scripts | grep -v -e /)

deploy: .dapper dapper-image clusters

$(TARGETS): .dapper dapper-image
	./.dapper -m bind $@

.DEFAULT_GOAL := ci

.PHONY: $(TARGETS)
