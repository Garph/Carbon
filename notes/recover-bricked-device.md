# Recovering Bricked EFR32BG22 Thunderboards

While testing fault exceptions handlers I encountered
reset loops that prevented a debugger from connecting to the device. Luckily,
Simplicity Studio ships with a means of recovering bricked devices:
```
$ ~/Software/SimplicityStudio_v5/developer/adapter_packs/commander/commander device recover
```
The Simplicity Commander GUI does not work with the EFR32BG22 at the time of 
writing, so it seems the CLI is the only way to recover.
