# cis_x01
## CIS X01 - Day 2
[If you're just starting, click here](tree/day-1)

## Instructions

Today we switch from a client to a server. This is a very simple, single threaded, single client, polling server. What does that mean? /Single threaded/ means we will only have one copy of the code running at a time. /Single client/ means that only one web browser can connect at a time. /Polling/ allows us to check if we have data and do other things if we need to until data is available, and then go through the read procedure. Without polling we would just stop at the line where we try to read data.
