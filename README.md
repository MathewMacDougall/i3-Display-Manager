# i3-Display-Manager

## Goals
- automatic monitor detection
- automatic DPI configuration / scaling configuration
- automatically save and restore monitor positions
- mirror by default on new monitors (mirror to what?? use smallest resolution of two monitors)
- save what workspaces are on what monitor

## Notes
- monitor is saved by position in yaml file
- primary monitor is indicated in yaml file
- dpi / scaling is automatic
- GUI runs directly off the backend
- backend uses yaml for persistant state
