#include <Windows.h>

void gaurd_memory() {
	unsigned char* memory_region = NULL;
	LPVOID memory_address = NULL;

	//Define the memory address of where you are executing your file

	//Allocate a memory region using PAGE_NOACCESS, which gaurds the memory region
	memory_region = (unsigned char*)VirtualAlloc(memory_address, sizeof(memory_address),
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	//Check if allocation was succesfull
	if (memory_region == NULL) {
		printf(_("Invalid memory region \n"));

		//Here you can try allocate memory at an arbitrary position
		memory_region = (unsigned char*)VirtualAlloc(memory_address, sizeof(memory_address),
			MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		//If it fails again, that means you are out of memory
		if (memory_region == NULL) {
			SetLastError(ERROR_OUTOFMEMORY);
		}
	}
	
	//Load whatever you want to execute
	
	//Gaurd the memory region
	DWORD gaurd;
  	VirtualProtect(memory_region, sizeof(memory_region), PAGE_NOACCESS, &gaurd);
	
	//Execute what you loaded

	//Check if the gaurded memory region has been accessed
	//To be more efficient, you could run this in a thread, and close the thread after you have free'd all memory
	MEMORY_BASIC_INFORMATION mbi{};
	VirtualQuery(memory_region, &mbi, sizeof(mbi));
	if (mbi.Protect != PAGE_NOACCESS) {
		//Clear and free all memory of your PE
		ZeroMemory(memory_address, sizeof(memory_address));
		VirtualFree(memory_address, sizeof(memory_address), MEM_RELEASE);

		exit(0);
	}

	//Erase all the memory from that specific address
	ZeroMemory(memory_address, sizeof(memory_address));

	//Free the memory
	VirtualFree(memory_address, sizeof(memory_address), MEM_RELEASE);
}
