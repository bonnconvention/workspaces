<?php

$sites = [
  'aewa' => 'tcworkspace.aewa.info',
  'ascobans' => 'workspace.ascobans.org',
  'cms' => 'workspace.cms.int',
  'eurobats' => 'workspace.eurobats.org',
  'workspace.cms.int.sharks' => 'workspace.cms.int/raptors',
  'workspace.cms.int.raptors' => 'workspace.cms.int/sharks',
];

foreach ($sites as $directory => $url) {

  $aliases["{$directory}"] = ['uri' => $directory];

  $aliases["{$directory}.prod"] = [
      'root' => '/var/local/workspaces/docroot',
      'remote-host' => 'www.unep-aewa.org',
      'remote-user' => 'php',
    ] + ['uri' => $directory];
}

// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}

