vim.g.mapleader = " "
vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1


-- lazy package manager
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system({
    "git",
    "clone",
    "--filter=blob:none",
    "https://github.com/folke/lazy.nvim.git",
    "--branch=stable", -- latest stable release
    lazypath,
  })
end
vim.opt.rtp:prepend(lazypath)

-- run lazy pkg manager
require("lazy").setup("plugins", {
  change_detection = {
    notify = false,
  },
})

-- some base config in ./lua/base.lua
require('base')

local my_opts = { noremap = true, silent = true }

----------------------------------------------------------plugins------------------------------------------------------------

-- 'lukas-reineke/indent-blankline.nvim'
local highlight = {
  "CursorColumn",
  "Whitespace",
}
require("ibl").setup {
  indent = { highlight = highlight, char = "" },
  whitespace = {
    highlight = highlight,
    remove_blankline_trail = false,
  },
  scope = { enabled = false },
}


-- 'simrat39/symbols-outline.nvim'
local opts = {
  highlight_hovered_item = true,
  show_guides = true,
  auto_preview = false,
  position = 'right',
  relative_width = true,
  width = 25,
  auto_close = false,
  show_numbers = false,
  show_relative_numbers = false,
  show_symbol_details = true,
  preview_bg_highlight = 'Pmenu',
  autofold_depth = 2,
  auto_unfold_hover = true,
  fold_markers = { '', '' },
  wrap = false,
  keymaps = { -- These keymaps can be a string or a table for multiple keys
    close = { "<Esc>", "q" },
    goto_location = "<Cr>",
    focus_location = "o",
    hover_symbol = "<C-space>",
    toggle_preview = "K",
    rename_symbol = "r",
    code_actions = "a",
    fold = "h",
    unfold = "l",
    fold_all = "W",
    unfold_all = "E",
    fold_reset = "R",
  },
  lsp_blacklist = {},
  symbol_blacklist = {},
  -- symbols = {
  --   File = { icon = "", hl = "@text.uri" },
  --   Module = { icon = "", hl = "@namespace" },
  --   Namespace = { icon = "", hl = "@namespace" },
  --   Package = { icon = "", hl = "@namespace" },
  --   Class = { icon = "𝓒", hl = "@type" },
  --   Method = { icon = "ƒ", hl = "@method" },
  --   Property = { icon = "", hl = "@method" },
  --   Field = { icon = "", hl = "@field" },
  --   Constructor = { icon = "", hl = "@constructor" },
  --   Enum = { icon = "ℰ", hl = "@type" },
  --   Interface = { icon = "ﰮ", hl = "@type" },
  --   Function = { icon = "", hl = "@function" },
  --   Variable = { icon = "", hl = "@constant" },
  --   Constant = { icon = "", hl = "@constant" },
  --   String = { icon = "𝓐", hl = "@string" },
  --   Number = { icon = "#", hl = "@number" },
  --   Boolean = { icon = "⊨", hl = "@boolean" },
  --   Array = { icon = "", hl = "@constant" },
  --   Object = { icon = "⦿", hl = "@type" },
  --   Key = { icon = "🔐", hl = "@type" },
  --   Null = { icon = "NULL", hl = "@type" },
  --   EnumMember = { icon = "", hl = "@field" },
  --   Struct = { icon = "𝓢", hl = "@type" },
  --   --Event = { icon = "🗲", hl = "@type" },
  --   Operator = { icon = "+", hl = "@operator" },
  --   TypeParameter = { icon = "𝙏", hl = "@parameter" },
  --   Component = { icon = "", hl = "@function" },
  --   Fragment = { icon = "", hl = "@constant" },
  -- },
}
require("symbols-outline").setup(opts)
vim.keymap.set("n", "<A-3>", ":SymbolsOutline<CR>", my_opts)


-- 'nvim-lualine/lualine.nvim'
require('lualine').setup {
  options = {
    theme = "catppuccin"
  }
}

-- 'akinsho/toggleterm.nvim
require("toggleterm").setup {
  open_mapping = [[<A-1>]],
  autochdir = true,
  direction = 'float',
}
vim.keymap.set('t', '<esc>', [[<C-\><C-n>]], my_opts)
vim.keymap.set('t', 'jk', [[<C-\><C-n>]], my_opts)



-- 'ibhagwan/fzf-lua'
vim.keymap.set('n', '<leader>f', ':FzfLua files<CR>', my_opts)

-- 'akinsho/bufferline.nvim'
require("bufferline").setup {}
vim.keymap.set('n', '<leader>bn', ':BufferLineCycleNext<CR>', my_opts)
vim.keymap.set('n', '<leader>bp', ':BufferLineCyclePrev<CR>', my_opts)
vim.keymap.set('n', '<leader>bl', ':BufferLineCloseRight<CR>', my_opts)
vim.keymap.set('n', '<leader>bh', ':BufferLineCloseLeft<CR>', my_opts)

-- 'windwp/nvim-autopairs'
require("nvim-autopairs").setup {}
-- If you want insert `(` after select function or method item
local cmp_autopairs = require('nvim-autopairs.completion.cmp')
local cmp = require('cmp')
cmp.event:on(
  'confirm_done',
  cmp_autopairs.on_confirm_done()
)

-- 'nvim-tree/nvim-tree.lua'
vim.keymap.set('n', '<A-2>', ':NvimTreeToggle<CR>', my_opts)
require("nvim-tree").setup({
  sort_by = "case_sensitive",
  sync_root_with_cwd = true,
  renderer = {
    group_empty = true,
  },
  filters = {
    dotfiles = true,
  },
})

-- 'nvim-treesitter/nvim-treesitter'
require 'nvim-treesitter.configs'.setup {
  -- A list of parser names, or "all" (the five listed parsers should always be installed)
  -- ensure_installed = { "c", "lua", "vim", "vimdoc", "query", "rust", "cpp", "nix" },
  ensure_installed = { cpp },

  -- Install parsers synchronously (only applied to `ensure_installed`)
  sync_install = false,

  -- Automatically install missing parsers when entering buffer
  -- Recommendation: set to false if you don't have `tree-sitter` CLI installed locally
  auto_install = false,

  -- List of parsers to ignore installing (for "all")
  ignore_install = { "javascript" },

  ---- If you need to change the installation directory of the parsers (see -> Advanced Setup)
  -- parser_install_dir = "/some/path/to/store/parsers", -- Remember to run vim.opt.runtimepath:append("/some/path/to/store/parsers")!

  highlight = {
    enable = true,
    -- NOTE: these are the names of the parsers and not the filetype. (for example if you want to
    -- disable highlighting for the `tex` filetype, you need to include `latex` in this list as this is
    -- the name of the parser)
    -- list of language that will be disabled
    --disable = { "c", "rust" },
    -- Or use a function for more flexibility, e.g. to disable slow treesitter highlight for large files
    disable = function(lang, buf)
      local max_filesize = 100 * 1024 -- 100 KB
      local ok, stats = pcall(vim.loop.fs_stat, vim.api.nvim_buf_get_name(buf))
      if ok and stats and stats.size > max_filesize then
        return true
      end
    end,

    -- Setting this to true will run `:h syntax` and tree-sitter at the same time.
    -- Set this to `true` if you depend on 'syntax' being enabled (like for indentation).
    -- Using this option may slow down your editor, and you may see some duplicate highlights.
    -- Instead of true it can also be a list of languages
    additional_vim_regex_highlighting = false,
  },
}

-- 'numToStr/Comment.nvim'
require('Comment').setup {
  mappings = {
    ---Operator-pending mapping; `gcc` `gbc` `gc[count]{motion}` `gb[count]{motion}`
    basic = false,
    ---Extra mapping; `gco`, `gcO`, `gcA`
    extra = false,
  },
}
vim.keymap.set("n", "<leader>/", "<cmd>lua require('Comment.api').toggle.linewise.current()<CR>", my_opts)
vim.keymap.set("x", "<leader>/", "<esc><cmd>lua require('Comment.api').toggle.linewise(vim.fn.visualmode())<CR>", my_opts)

-- "neovim/nvim-lspconfig"
-- Global mappings.
-- See `:help vim.diagnostic.*` for documentation on any of the below functions
vim.keymap.set('n', '<space>le', vim.diagnostic.open_float)
vim.keymap.set('n', '[d', vim.diagnostic.goto_prev)
vim.keymap.set('n', ']d', vim.diagnostic.goto_next)
vim.keymap.set('n', '<space>lq', vim.diagnostic.setloclist)

-- Use LspAttach autocommand to only map the following keys
-- after the language server attaches to the current buffer
vim.api.nvim_create_autocmd('LspAttach', {
  group = vim.api.nvim_create_augroup('UserLspConfig', {}),
  callback = function(ev)
    -- Enable completion triggered by <c-x><c-o>
    vim.bo[ev.buf].omnifunc = 'v:lua.vim.lsp.omnifunc'

    -- Buffer local mappings.
    -- See `:help vim.lsp.*` for documentation on any of the below functions
    local opts = { buffer = ev.buf }
    vim.keymap.set('n', 'gD', vim.lsp.buf.declaration, opts)
    vim.keymap.set('n', 'gd', vim.lsp.buf.definition, opts)
    vim.keymap.set('n', 'K', vim.lsp.buf.hover, opts)
    vim.keymap.set('n', 'gi', vim.lsp.buf.implementation, opts)
    vim.keymap.set('n', '<C-k>', vim.lsp.buf.signature_help, opts)
    vim.keymap.set('n', '<leader>lwa', vim.lsp.buf.add_workspace_folder, opts)
    vim.keymap.set('n', '<leader>lwr', vim.lsp.buf.remove_workspace_folder, opts)
    vim.keymap.set('n', '<leader>lwl', function()
      print(vim.inspect(vim.lsp.buf.list_workspace_folders()))
    end, opts)
    vim.keymap.set('n', '<leader>D', vim.lsp.buf.type_definition, opts)
    vim.keymap.set('n', '<leader>rn', vim.lsp.buf.rename, opts)
    vim.keymap.set({ 'n', 'v' }, '<leader>ca', vim.lsp.buf.code_action, opts)
    vim.keymap.set('n', 'gr', vim.lsp.buf.references, opts)
    vim.keymap.set('n', '<leader>lf', function()
      vim.lsp.buf.format { async = true }
    end, opts)
    if vim.lsp.inlay_hint then
      vim.keymap.set(
        "n",
        "<leader>lh",
        function()
          vim.lsp.inlay_hint(0, nil)
        end,
        { desc = "Toggle Inlay Hints" }
      )
    end
  end,
})

-- 'ggandor/leap.nvim'
require('leap').add_default_mappings()


-- try to fix the popup windows width
-- references: https://github.com/hrsh7th/nvim-cmp/issues/980#issuecomment-1121773499
local ELLIPSIS_CHAR = '…'
local MAX_LABEL_WIDTH = 20
local MIN_LABEL_WIDTH = 20

-- Set up nvim-cmp.
local cmp = require 'cmp'

cmp.setup({
  formatting = {
    -- try to fix the popup windows width
    format = function(entry, vim_item)
      local label = vim_item.abbr
      local truncated_label = vim.fn.strcharpart(label, 0, MAX_LABEL_WIDTH)
      if truncated_label ~= label then
        vim_item.abbr = truncated_label .. ELLIPSIS_CHAR
      elseif string.len(label) < MIN_LABEL_WIDTH then
        local padding = string.rep(' ', MIN_LABEL_WIDTH - string.len(label))
        vim_item.abbr = label .. padding
      end
      return vim_item
    end,
  },
  snippet = {
    -- REQUIRED - you must specify a snippet engine
    expand = function(args)
      --vim.fn["vsnip#anonymous"](args.body) -- For `vsnip` users.
      require('luasnip').lsp_expand(args.body) -- For `luasnip` users.
      -- require('snippy').expand_snippet(args.body) -- For `snippy` users.
      -- vim.fn["UltiSnips#Anon"](args.body) -- For `ultisnips` users.
    end,
  },
  window = {
    -- make neovim hoverbox have border
    completion = cmp.config.window.bordered(),
    documentation = cmp.config.window.bordered(),
  },
  mapping = cmp.mapping.preset.insert({
    ['<C-b>'] = cmp.mapping.scroll_docs(-4),
    ['<C-f>'] = cmp.mapping.scroll_docs(4),
    ['<C-Space>'] = cmp.mapping.complete(),
    ['<C-e>'] = cmp.mapping.abort(),
    -- ['<CR>'] = cmp.mapping.confirm({ select = true }), -- Accept currently selected item. Set `select` to `false` to only confirm explicitly selected items.
    -- I use tab for confirm, too
    ['<Tab>'] = cmp.mapping.confirm({ select = true }),
  }),
  sources = cmp.config.sources({
    { name = 'nvim_lsp' },
    -- { name = 'vsnip' }, -- For vsnip users.
    { name = 'luasnip' }, -- For luasnip users.
    -- { name = 'ultisnips' }, -- For ultisnips users.
    -- { name = 'snippy' }, -- For snippy users.
  }, {
    { name = 'buffer' },
  })
})

-- Set configuration for specific filetype.
cmp.setup.filetype('gitcommit', {
  sources = cmp.config.sources({
    { name = 'git' }, -- You can specify the `git` source if [you were installed it](https://github.com/petertriho/cmp-git).
  }, {
    { name = 'buffer' },
  })
})

-- Use buffer source for `/` and `?` (if you enabled `native_menu`, this won't work anymore).
cmp.setup.cmdline({ '/', '?' }, {
  mapping = cmp.mapping.preset.cmdline(),
  sources = {
    { name = 'buffer' }
  }
})

-- Use cmdline & path source for ':' (if you enabled `native_menu`, this won't work anymore).
cmp.setup.cmdline(':', {
  mapping = cmp.mapping.preset.cmdline(),
  sources = cmp.config.sources({
    { name = 'path' }
  }, {
    { name = 'cmdline' }
  })
})

require("mason").setup()
require("mason-lspconfig").setup()

----------------------------------------plugins end-----------------------------------------------


-- lsp config
local capabilities = require('cmp_nvim_lsp').default_capabilities()


-- Setup language servers.
local lspconfig = require('lspconfig')

lspconfig.lua_ls.setup {
  capabilities = capabilities,
  settings = {
    Lua = {
      runtime = {
        -- Tell the language server which version of Lua you're using (most likely LuaJIT in the case of Neovim)
        version = 'LuaJIT',
      },
      diagnostics = {
        -- Get the language server to recognize the `vim` global
        globals = { 'vim' },
      },
      hint = { enable = true },
      workspace = {
        -- Make the server aware of Neovim runtime files
        library = vim.api.nvim_get_runtime_file("", true),
        checkThirdParty = false, -- THIS IS THE IMPORTANT LINE TO ADD
      },
      -- Do not send telemetry data containing a randomized but unique identifier
      telemetry = {
        enable = false,
      },
    },
  },
}

lspconfig.pyright.setup {
  capabilities = capabilities
}


-- lspconfig.pyright.setup {
--   capabilities = capabilities,
--   settings = {
--     pyright = { autoImportCompletion = true, },
--     python = {
--       analysis = {
--         autoSearchPaths = true,
--         diagnosticMode = 'openFilesOnly',
--         useLibraryCodeForTypes = true,
--         typeCheckingMode = 'off'
--       }
--     }
--   }
-- }


lspconfig.rust_analyzer.setup {
  capabilities = capabilities,
  -- Server-specific settings. See `:help lspconfig-setup`
  settings = {
    ['rust-analyzer'] = {},
  },
}

lspconfig.clangd.setup {
  cmd = { "clangd", "--header-insertion=never", "--inlay-hints=true" },
  capabilities = capabilities,
  hint = { enable = true },
}

lspconfig.bashls.setup {
  capabilities = capabilities
}

-- lspconfig.gopls.setup {
--   capabilities = capabilities
-- }
--
-- lspconfig.nil_ls.setup {
--   autostart = true,
--   capabilities = capabilities,
--   settings = {
--     ['nil'] = {
--       testSetting = 42,
--       formatting = {
--         command = { "nixfmt" },
--       },
--     },
--   },
-- }


-- make .zshrc highlight like bash file
vim.api.nvim_create_autocmd({ "BufEnter", "BufWinEnter" }, {
  pattern = { ".zshrc" },
  callback = function()
    require("nvim-treesitter.highlight").attach(0, "bash")
  end
})


-- I like 4 spaces indent
vim.cmd('autocmd FileType cpp setlocal shiftwidth=4')

-- show copy filed when copy
vim.cmd [[
augroup highlight_yank
    autocmd!
    au TextYankPost * silent! lua vim.highlight.on_yank { higroup='IncSearch', timeout=200 }
augroup END
]]


vim.cmd [[
set signcolumn=yes
autocmd CursorHold * lua vim.lsp.buf.document_highlight()
autocmd CursorMoved * lua vim.lsp.buf.clear_references()
]]
