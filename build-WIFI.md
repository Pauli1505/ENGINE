# This build requires wifi, but is more efficient because it builds all platforms for all architectures.
# NOTE: 32 bit does not support running OpenSandbox and QytrineTest
# anymore, because its supposed to allocate  a few bytes for storing sound, but this is done via 64 bit code, causing it to crash and error out.

# The script

# replace YOUR_GITHUB_TOKEN and api.github.com/repos/OWNER/REPO/ with your own credentials
# example api.github.com/xx:
# https://api.github.com/repos/Pauli1505/Cytrine2/actions/workflows/build.yml/dispatches
# this assumes my user is Pauli1505, my repository is called Cytrine2 and my workflow file is build.yml.
# make sure you are running a self-hosted runner to execute it.
curl -X POST \
-H "Authorization: token YOUR_GITHUB_TOKEN" \
-H "Accept: application/vnd.github.v3+json" \
-d '{"event_type": "trigger_workflow"}' \
https://api.github.com/repos/OWNER/REPO/dispatches

# at the time of this being committed, there wont be any 32 bit builds left as they are rendered unusable.