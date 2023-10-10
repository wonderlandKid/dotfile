local wezterm = require 'wezterm'
local config = {}



--字体配置
config.font = wezterm.font_with_fallback {
  {
    family = 'JetBrainsMonoNL Nerd Font',
    weight = 'Medium',
    harfbuzz_features = { 'calt=0', 'clig=0', 'liga=0' },
  },
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

-- config.window_background_opacity = 0.9

-- How many lines of scrollback you want to retain per tab
config.scrollback_lines = 5000

-- Enable the scrollbar.
-- It will occupy the right window padding space.
-- If right padding is set to 0 then it will be increased
-- to a single cell width
config.enable_scroll_bar = true

-- config.window_background_image = '/home/liu/.config/wezterm/linm.jpg'
--
-- config.window_background_image_hsb = {
--   -- Darken the background image by reducing it to 1/3rd
--   brightness = 0.1,
--
--   -- You can adjust the hue by scaling its value.
--   -- a multiplier of 1.0 leaves the value unchanged.
--   hue = 1.0,
--
--   -- You can adjust the saturation also.
--   saturation = 1.0,
-- }
--

local dimmer = { brightness = 0.05 } -- 调整亮度的参数
config.background = {
  {
    source = {
      File = '/home/liu/.config/wezterm/linm.jpg',
    },
    width = 1920,  -- 你期望的壁纸宽度
    height = 1080, -- 你期望的壁纸高度
    repeat_x = 'NoRepeat',
    repeat_y = 'NoRepeat',
    attachment = 'Fixed',        -- 固定不随滚动而移动
    horizontal_align = 'Center', -- 水平居中
    vertical_align = 'Middle',   -- 垂直居中
    hsb = dimmer,
  },
  -- 其他层次的背景配置
}

return config
