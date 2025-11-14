# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "AUDIO_BIT_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "BIT_HEIGHT" -parent ${Page_0}
  ipgui::add_param $IPINST -name "BIT_WIDTH" -parent ${Page_0}


}

proc update_PARAM_VALUE.AUDIO_BIT_WIDTH { PARAM_VALUE.AUDIO_BIT_WIDTH } {
	# Procedure called to update AUDIO_BIT_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.AUDIO_BIT_WIDTH { PARAM_VALUE.AUDIO_BIT_WIDTH } {
	# Procedure called to validate AUDIO_BIT_WIDTH
	return true
}

proc update_PARAM_VALUE.BIT_HEIGHT { PARAM_VALUE.BIT_HEIGHT } {
	# Procedure called to update BIT_HEIGHT when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.BIT_HEIGHT { PARAM_VALUE.BIT_HEIGHT } {
	# Procedure called to validate BIT_HEIGHT
	return true
}

proc update_PARAM_VALUE.BIT_WIDTH { PARAM_VALUE.BIT_WIDTH } {
	# Procedure called to update BIT_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.BIT_WIDTH { PARAM_VALUE.BIT_WIDTH } {
	# Procedure called to validate BIT_WIDTH
	return true
}


proc update_MODELPARAM_VALUE.AUDIO_BIT_WIDTH { MODELPARAM_VALUE.AUDIO_BIT_WIDTH PARAM_VALUE.AUDIO_BIT_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.AUDIO_BIT_WIDTH}] ${MODELPARAM_VALUE.AUDIO_BIT_WIDTH}
}

proc update_MODELPARAM_VALUE.BIT_WIDTH { MODELPARAM_VALUE.BIT_WIDTH PARAM_VALUE.BIT_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.BIT_WIDTH}] ${MODELPARAM_VALUE.BIT_WIDTH}
}

proc update_MODELPARAM_VALUE.BIT_HEIGHT { MODELPARAM_VALUE.BIT_HEIGHT PARAM_VALUE.BIT_HEIGHT } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.BIT_HEIGHT}] ${MODELPARAM_VALUE.BIT_HEIGHT}
}

