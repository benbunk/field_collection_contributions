<?php

/**
 * Print a single row of multiple fields.
 */
function theme_field_collection_contributions_meter($variables) {
  drupal_add_css(drupal_get_path('module', 'field_collection_contributions') . '/theme/css/field_collection_contributions.css');
  $current = $variables['current'];
  $goal = $variables['goal'];

  $target_amount = $variables['goal'] * 100;
  $contributions = $variables['current'] * 100;

  //height of the dynamic meter area
  $height = 324;

  $current_height = ($contributions * $height) / $target_amount;

  $current_amount_height = $current_height + 73;

  $html = '<div id="commerce_contributions_meter">
    <div id="commerce_contributions_contributions" style="height: ' . $current_height . 'px;"></div>
    <span id="amount1">' . commerce_currency_format($target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount2">' . commerce_currency_format(2 * $target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount3">' . commerce_currency_format(3 * $target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount4">' . commerce_currency_format(4 * $target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount5">' . commerce_currency_format(5 * $target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount6">' . commerce_currency_format(6 * $target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount7">' . commerce_currency_format(7 * $target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount8">' . commerce_currency_format(8 * $target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount9">' . commerce_currency_format(9 * $target_amount / 10, commerce_default_currency()) . '</span>
    <span id="amount10">' . commerce_currency_format($target_amount, commerce_default_currency()) . '</span>
    <span id="current_amount" style="bottom: ' . $current_amount_height . 'px;">' . commerce_currency_format($contributions, commerce_default_currency()) . '</span>
    </div>';

  return $html;
}
