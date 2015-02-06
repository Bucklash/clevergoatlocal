<?php
/**
 * @file
 * Contains the privacypu argument validator plugin.
 */

/**
 * Provide privacypu access check to validate whether or not an argument is ok.
 *
 * @ingroup views_argument_validate_plugins
 */
class privacypu_plugin_argument_validate_privacypu extends views_plugin_argument_validate {
  function option_definition() {
    $options = parent::option_definition();
    $options['privacypu'] = array('default' => array());

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['privacypu'] = array(
      '#type' => 'select',
      '#title' => t('Privacy type'),
      '#options' => privacypu_types_options(),
      '#default_value' => $this->options['privacypu'],
      '#description' => t('Choose the privacy type for this view.  If you do not see the type that you need, you may add it in the Privacy Per User admin page.'),
    );

    $this->check_access($form, 'privacypu');
  }

  function validate_argument($argument) {
    return privacypu_check_access(user_load($argument), $this->options['privacypu']);
  }
}
