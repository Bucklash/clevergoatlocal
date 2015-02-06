<?php
/**
 * @file
 * Admin settings for Privacy Per User.
 */

/**
 * Admin settings form.
 */
function privacypu_admin_settings() {
  $form = array();
  $options = privacypu_states_options();

  $form['privacypu_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );

  $form['privacypu_defaults']['privacypu_default_state'] = array(
    '#type' => 'select',
    '#title' => t('Global default privacy state'),
    '#description' => t('This privacy state will be used for any user that has not already specified a privacy state.  This may be overridden per privacy type.'),
    '#options' => $options,
    '#default_value' => variable_get('privacypu_default_state', 'private'),
  );

  return system_settings_form($form);
}
