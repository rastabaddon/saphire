-- START GUI
print("init GUI")

Menus = {}

include "startGUI.lua"


Menus.showMenu = function(this,name)
			if(this[name]) then
			    this:hideAllMenu();
			    print("Show GUI: "..name);	
			    this[name]:showGui(true);	
			    return true;	
			else
			    error("GUI not exist: "..name);
			    return false;	
			end
		 end


Menus.hideMenu = function(this,name)
			if(this[name]) then
			    print("Hide GUI: "..name);	
			    this[name]:showGui(false);	
			    return true;	
			else
			    error("GUI not exist: "..name);
			    return false;	
			end
		 end

Menus.hideAllMenu = function(this)
			    print("Hide all menus ");	
		    end
