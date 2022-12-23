# GuardMemory-Region

## Information

This is a short, yet simple way of gaurding memory regions. This example uses PAGE_NOACCESS to create a memory region in an arbitary position, which then allows you to execute your file inside of it. It also has a check on if the gaurded memory region was accessed, and if it was it clears all memory and exits. This can be used to execute a PE file directly in memory, in a more "safe" way.


## Downsides

You will need to get the memory address yourself, i did not provide a way on how to do it. There are many ways to do this, a quick google search should help you out if you are not sure what to do.
