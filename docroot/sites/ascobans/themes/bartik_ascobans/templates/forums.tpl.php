<?php

/**
 * @file
 * Displays a forum.
 *
 * May contain forum containers as well as forum topics.
 *
 * Available variables:
 * - $forums: The forums to display (as processed by forum-list.tpl.php).
 * - $topics: The topics to display (as processed by forum-topic-list.tpl.php).
 * - $forums_defined: A flag to indicate that the forums are configured.
 *
 * @see template_preprocess_forums()
 *
 * @ingroup themeable
 */
?>
<div>The <b>Discussion Area</b> contains forums where users can discuss any matters not covered under <a href="http://workspace.ascobans.org/node/258">Working Groups</a>. This area should be reserved for matters of relevance for the entire Advisory Committee, which will mostly be of an administrative or technical nature.<br><br>Anything related to the topics covered either by an official regional or thematic working group, or otherwise contained in the Advisory Committee’s work plan (see <b>Other Topics</b> under <a href="http://workspace.ascobans.org/node/258">Working Groups</a>), should be posted in the appropriate discussion thread in that section of the workspace.</div>
<?php if ($forums_defined): ?>
<div id="forum">
  <?php print $forums; ?>
  <?php print $topics; ?>
</div>
<?php endif; ?>
