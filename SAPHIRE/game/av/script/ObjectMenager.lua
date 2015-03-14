if ObjectMenager==nil then
	ObjectMenager = {}
end

include "ObjectCar.lua"

ObjectMenager.addVehicle = function (self,vehicleName,scene)

	xml = Resource:loadIniFile("defs/"..vehicleName..".def");
	if(xml) then

		if(xml.Body.Type=="CAR") then
			return self:addCar(xml,scene)
		end

		return false;
	else
		error ("Can`t load vehicle")		
		return false;
	end
end

ObjectMenager.addForest = function (self,name,scene,x,y,z)

	for ax = 1, 10 do
		for az = 1, 10 do
			tree = Object:createObject(Object.STATIC,"obj/"..name);
			if(tree) then
				tree:setPosition(x+(2*ax),y,z+(2*az));
				scene:addObject(tree);
			end
		end
	end
	
end

