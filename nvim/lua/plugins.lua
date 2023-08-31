return {
  "neovim/nvim-lspconfig",
  "williamboman/mason.nvim",
  "williamboman/mason-lspconfig.nvim",

  'hrsh7th/cmp-nvim-lsp',
  'hrsh7th/cmp-buffer',
  'hrsh7th/cmp-path',
  'hrsh7th/cmp-cmdline',
  'hrsh7th/nvim-cmp',
  'L3MON4D3/LuaSnip',
  'saadparwaiz1/cmp_luasnip',

  'numToStr/Comment.nvim',
  'simrat39/symbols-outline.nvim',
  'ggandor/leap.nvim',
  'lukas-reineke/indent-blankline.nvim',

  {
    'akinsho/bufferline.nvim',
    version = "*",
    dependencies = 'nvim-tree/nvim-web-devicons'
  },
  {
    'nvim-tree/nvim-tree.lua',
    requires = {
      'nvim-tree/nvim-web-devicons',
      -- optional, for file icons
    },
  },
  {
    'ibhagwan/fzf-lua',
    -- optional for icon support
    requires = { 'nvim-tree/nvim-web-devicons' }
  },
  {
    'akinsho/toggleterm.nvim',
    version = "*",
    config = true
  },
  {
    'nvim-lualine/lualine.nvim',
    requires = { 'nvim-tree/nvim-web-devicons', opt = true }
  },
  {
    'windwp/nvim-autopairs',
    event = "InsertEnter",
    opts = {} -- this is equalent to setup({}) function
  },
  {
    'nvim-treesitter/nvim-treesitter',
    run = ':TSUpdate'
  },
  {
    "catppuccin/nvim",
    as = "catppuccin",
    lazy = false,
    priority = 1000,
    config = function()
      -- load the colorscheme here
      vim.cmd([[colorscheme catppuccin-macchiato]])
    end,
  },
}
