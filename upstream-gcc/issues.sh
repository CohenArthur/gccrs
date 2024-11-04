#!/bin/env sh

gh issue list -L 1
gh issue list -L 1 -S "is:closed"
gh issue list -L 1 -S "no:assignee"

gh issue list -L 1 -l "bug"
gh issue list -L 1 -l "bug" -S "is:closed"
gh issue list -L 1 -l "bug" -S "no:assignee"
