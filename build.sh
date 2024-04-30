#!/bin/bash

find "demo/bin/"* ! -name "*.gdextension" -exec rm {} \;  && scons platform=windows build_library=no