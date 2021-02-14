

# Set this macro to 'VCNT' to use the Visual C++ tools.
# Set it to anything else to use the Win32 SDK tools.

TOOLS = VCNT

!IF "$(TOOLS)" == "VCNT"

LINK = link

!ELSE

LINK = link32

!ENDIF


all:
      ml /c /coff /Zi encryptor.asm
      $(LINK) -incremental:no -subsystem:console -entry:mainCRTStartup -out:encryptor1.exe \
	 encryptor.obj kernel32.lib libc.lib -DEBUG
