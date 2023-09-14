local wezterm = require 'wezterm'
local config = {}



--字体配置
config.font = wezterm.font_with_fallback {
  'JetBrainsMono Nerd Font',
  'SFMono Nerd Font',
  '思源黑体 CN',
}

-- config.disable_default_key_bindings = true


local act = wezterm.action
config.keys = {
  { key = 'e', mods = 'CTRL|SHIFT', action = act.SplitHorizontal { domain = 'CurrentPaneDomain' }, },
  { key = 'o', mods = 'CTRL|SHIFT', action = act.SplitVertical { domain = 'CurrentPaneDomain' }, },
  { key = 'f', mods = 'SHIFT|CTRL', action = act.Search { CaseInSensitiveString = '' }, },
  { key = 'n', mods = 'CMD',        action = act.SpawnCommandInNewTab, },
}

config.color_scheme = "Catppuccin Macchiato"

config.window_background_opacity = 0.9

-- How many lines of scrollback you want to retain per tab
config.scrollback_lines = 5000

-- Enable the scrollbar.
-- It will occupy the right window padding space.
-- If right padding is set to 0 then it will be increased
-- to a single cell width
config.enable_scroll_bar = true


return config
