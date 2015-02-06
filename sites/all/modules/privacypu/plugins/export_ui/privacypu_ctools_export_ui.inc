<?php
/**
 * @file
 * Enable the CTools export UI.
 */

/**
 * Define the Export UI plugin.
 */
$plugin = array(
  'schema' => 'privacypu_types',
  'access' => 'administer site configuration',
  'menu' => array(
    'menu item' => 'privacypu',
    'menu title' => 'Privacy Per User',
    'menu description' => 'Administer privacy types.',
  ),
  'title singular' => t('privacy type'),
  'title plural' => t('privacy types'),
  'title singular proper' => t('Privacy type'),
  'title plural proper' => t('Privacy types'),
  'form' => array(
    'settings' => 'privacypu_ctools_export_ui_form',
  ),
);

/**
 * Define the add/edit form.
 */
function privacypu_ctools_export_ui_form(&$form, &$form_state) {
  $privacy_type = $form_state['item'];

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The human readable name of this privacy type.'),
    '#default_value' => $privacy_type->title,
    '#required' => TRUE,
  );

  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#description' => t('The position of this privacy type on the user settings form. Smaller numbers rise to the top.  Larger numbers sink to the bottom.'),
    '#default_value' => $privacy_type->weight,
    '#delta' => 10,
  );

  $options = array('default' => t('Use global default privacy state')) + privacypu_states_options();

  $form['default_state'] = array(
    '#type' => 'select',
    '#title' => t('Default privacy state'),
    '#description' => t('The privacy state that will be used for any user that has not already specified a privacy state.  This will override the global default privacy state for just this privacy type.'),
    '#options' => $options,
    '#default_value' => $privacy_type->default_state,
  );
}
