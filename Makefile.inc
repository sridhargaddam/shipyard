k8s_version ?= 1.14.6
globalnet ?= false
deploytool ?= operator

SCRIPTS_DIR ?= /opt/shipyard/scripts

.dapper:
	@echo Downloading dapper
	@curl -sL https://releases.rancher.com/dapper/latest/dapper-`uname -s`-`uname -m` > .dapper.tmp
	@@chmod +x .dapper.tmp
	@./.dapper.tmp -v
	@mv .dapper.tmp .dapper

shell: .dapper
	./.dapper -m bind -s

cleanup: .dapper
	./.dapper -m bind $(SCRIPTS_DIR)/cleanup.sh

clusters: .dapper
	./.dapper -m bind $(SCRIPTS_DIR)/clusters.sh --k8s_version $(k8s_version) --globalnet $(globalnet)

deploy: .dapper clusters
	DAPPER_ENV="OPERATOR_IMAGE" ./.dapper -m bind $(SCRIPTS_DIR)/deploy.sh --globalnet $(globalnet) --deploytool $(deploytool)
