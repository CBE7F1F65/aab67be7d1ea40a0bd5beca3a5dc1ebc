LTable_SceneIDFunction	=
{
	{		
		Scene_s00,
		Scene_s01,
		Scene_s02,
		Scene_s03,
		Scene_s04,
		Scene_s05,
		Scene_s06,
		Scene_s07,
		Scene_s08,
		Scene_s09,
		Scene_s10,
		Scene_s11,
		Scene_s12,
		Scene_s13,
		Scene_s14,
		Scene_s15,
		Scene_s16,
		Scene_s17,
		Scene_s18,
		Scene_s19,
		Scene_s20,
		Scene_s21,
		Scene_s22,
		Scene_s23,
	},

	{
		Spell_s00,
		Spell_s01,
		Spell_s02,
		Spell_s03,
		Spell_s04,
		Spell_s05,
		Spell_s06,
		Spell_s07,
		Spell_s08,
		Spell_s09,
		Spell_s10,
		Spell_s11,
		Spell_s12,
		Spell_s13,
		Spell_s14,
		Spell_s15,
		Spell_s16,
		Spell_s17,
		Spell_s18,
		Spell_s19,
		Spell_s20,
		Spell_s21,
		Spell_s22,
		Spell_s23,
	}
}

function SceneExecute(name, timer)
	
	local playerindex = 0;
	if name >= PLAYERTYPEMAX and name < LConst_SceneSpellOffset or name-LConst_SceneSpellOffset >= PLAYERTYPEMAX then
		name = name - PLAYERTYPEMAX;
		playerindex = 1;
	end
	
	local scenespellindi = 1;
	local scenespellindex = name;
	if name >= LConst_SceneSpellOffset then
		scenespellindi = 2;
		scenespellindex = name - LConst_SceneSpellOffset;
	end
	return LTable_SceneIDFunction[scenespellindi][scenespellindex+1](playerindex, timer);
--	for i, it in pairs(LTable_SceneIDFunction) do
--		if it[1] == name then
--			return it[2](playerindex, timer);
--		end
--	end

end