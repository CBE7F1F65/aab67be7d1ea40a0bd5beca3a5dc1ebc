LTable_SceneIDFunction	=
{
	Scene_s00,
}

function SceneExecute(area, timer)
	
	return LTable_SceneIDFunction[area+1](timer);

end