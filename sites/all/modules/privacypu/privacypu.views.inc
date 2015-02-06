<?php
/**
 * @file
 * Provide a Views plugin for privacypu module.
 */

/**
 * Implements hook_views_plugins().
 */
function privacypu_views_plugins() {
  return array(
    'argument validator' => array(
      'privacypu' => array(
        'title' => t('Privacy Per User'),
        'handler' => 'privacypu_plugin_argument_validate_privacypu',
      ),
    ),
  );
}
