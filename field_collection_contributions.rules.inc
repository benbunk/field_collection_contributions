<?php

/**
 * @file
 * Rules for this field.
 */

/**
 * Implements hook_rules_action_info().
 */
function field_collection_contributions_rules_action_info() {
  $actions = array();

  $actions['commerce_checkout_contribution'] = array(
    'label' => t('Adjust product field.'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order in checkout'),
      ),
    ),
    'group' => t('Commerce Checkout'),
    'callbacks' => array(
      'execute' => 'field_collection_contributions_rules_complete_contribution',
    ),
  );

  return $actions;
}

/**
 * Increment a donation meter with the value of the donation once checkout is complete.
 *
 * @param $order
 */
function field_collection_contributions_rules_complete_contribution($order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  foreach ($order_wrapper->commerce_line_items->getIterator() as $delta => $line_item_wrapper) {
    if (!isset($product_wrapper)) {
      isset($line_item_wrapper->commerce_product) ? $product_wrapper = $line_item_wrapper->commerce_product->value() : NULL;
    }
  }

  // Go over the price components to figure out donation and fee.
  foreach($order->commerce_order_total['und'][0]['data']['components'] as $delta => $component) {
    if($component['name'] === 'base_price') {
      $donation = $component['price']['amount'];
    }
    if ($component['name'] === 'fee') {
      $fee = $component['price']['amount'];
    }
  }


  // If the charity is paying the fee take that out of the donation.
  // @todo - Figure out how to automatically calculate the fee with and without the using paying it.
  if (!isset($fee)) {
    $fee = $donation * .1;
    $donation = $donation - $fee;
  }
  $donation = commerce_currency_amount_to_decimal($donation, commerce_default_currency());

  // get fields on the product
  // @todo - Ben - Figure out why the product wrapper can't access the field_collection values.
  $meter_item = field_get_items('commerce_product', $product_wrapper, 'field_donation_meter');
  $item_collection = field_collection_field_get_entity($meter_item[0]);
  $meter_wrapper = entity_metadata_wrapper('field_collection_item', $item_collection);

  // Add donation to total donations.
  // @todo - Ben - Get field_donation_current as an input from the rule setup.
  $current = $meter_wrapper->field_donation_current->value();

  // @todo - Ben - Get field_donation_goal as an input from the rule setup.
  $goal = $meter_wrapper->field_donation_goal->value();
  if (($current + $donation) > $goal) {
    $current = $goal;
  }
  else {
    $current += $donation;
  }
  $meter_wrapper->field_donation_current->set($current);
  $meter_wrapper->save();
}
