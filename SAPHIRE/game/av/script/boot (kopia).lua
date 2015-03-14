-- ================================================================================
--  STANDARD BOOT SCRIPT
-- ================================================================================

print ("Advena Universi: The begining");

_Cfg:loadCfg ("/config/default.xml");

-- ================================================================================
--  NO GAMEMODE SHUTDOWN
-- ================================================================================
--shutDown();

Resource:loadAllResources("Av");

include "ObjectMenager.lua"

scene = Scene:createScene(0,0,0);
Scene:setCurrentScene(scene);

scene:setCameraPosition(0,5,0); --Main camera

player = Controler:createControler(Controler.PLAYER); -- With default key assign / obsluga myszy i klawiatury



--terrain = Object:createObject(Object.TERAIN,"obj/clearteren.3ds");
--terrain:setPosition(0,0,0);

--scene:addObject(terrain);

--[[
house = Object:createObject(Object.STATIC,"obj/house.3ds");
house:setPosition(50,-0.5,0);
scene:addObject(house);
]]

car = ObjectMenager:addVehicle("subaru",scene);
car:setPosition(10,2,10);
car:addControler(player); 
--car:saveToFile("subaru.sob");

--scene:addToDebug(car);

scene:setBuletDebug(false);

--ObjectMenager:addForest("tree.3ds",scene,30,1,30);


-- BOX SHAKE
--[[
for x=1,6 do
	for y=1,6 do
		for z=1,6 do
			box = Object:createObject(Object.DYNAMIC,"obj/box.3ds");
			box:setPosition(1.05*x,0.05+(1*z),1.05*y);
			scene:addObject(box);
		end
	end
end
]]

--[[
b1 = Object:createObject(Object.DYNAMIC,"obj/b1.3ds");
b1:setPosition(10,5,10);
scene:addObject(b1);
b1:setPosition(10,5,10);

b2 = Object:createObject(Object.DYNAMIC,"obj/b2.3ds");
b2:setPosition(20,5,20);
scene:addObject(b2);
b2:setPosition(20,5,20);

b3 = Object:createObject(Object.DYNAMIC,"obj/starship.3ds");
b3:setPosition(-20,5,-20);
scene:addObject(b3);
b3:setPosition(0,5,0);

]]

b1 = Object:createObject(Object.DYNAMIC,"obj/ped.x");
b1:setPosition(0,0,0);
scene:addObject(b1);
b1:setPosition(0,0,0);

b1 = Object:createObject(Object.STATIC,"obj/bigBox.3ds");
b1:setPosition(10,-10,10);
scene:addObject(b1);
b1:setPosition(10,-10,10);

for x=1,2 do
	for y=1,2 do
		for z=1,2 do
			b = Object:createObject(Object.DYNAMIC,"obj/box.3ds");
			b:setPosition((10*x),100+(10*z),(10*y));
			scene:addObject(b);
			b:setPosition((10*x),100+(10*z),(10*y));
		end
	end
end


Video:setLoadingScreenShowStatus(false);

--ped:setMass(0.1);
scene:setPause(false)

print("WSZYSTKO JUZ POWINNO ")

