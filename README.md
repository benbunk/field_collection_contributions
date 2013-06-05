field_collection_contributions
==============================

A field collection formatter for contributions. To replace commerce_contributions module.

Setup
==============================

1. Create a new field collection on the product variation type.

2. Add two fields to the collection (Until the rule is improved the field must have the correct machine names)
    1. Donation Current - field_donation_current - decimal
    2. Donation Goal - field_donation_goal - decimal

3. Manage the display of the field_collection on the product variation type to Contribution progress meter.

4. In the field display settings set Current Field to Donation Current, set Goal Field to Donation Goal.

5. Add a field called field_donation_amount on the product line item.

6. Add a rule to add the field_donation_amount to the line item unit price.
{ "rules_donation_to_total" : {
    "LABEL" : "Donation to Total",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "donation" ],
    "REQUIRES" : [ "rules", "commerce_line_item", "commerce_product_reference" ],
    "ON" : [ "commerce_product_calculate_sell_price" ],
    "IF" : [
      { "entity_has_field" : { "entity" : [ "commerce-line-item" ], "field" : "field_donation_amount" } }
    ],
    "DO" : [
      { "data_calc" : {
          "USING" : {
            "input_1" : [ "commerce-line-item:field-donation-amount" ],
            "op" : "*",
            "input_2" : "100"
          },
          "PROVIDE" : { "result" : { "donation_in_dollars" : "Donation amount in dollars" } }
        }
      },
      { "commerce_line_item_unit_price_amount" : {
          "commerce_line_item" : [ "commerce_line_item" ],
          "amount" : [ "donation-in-dollars" ],
          "component_name" : "base_price",
          "round_mode" : "1"
        }
      }
    ]
  }
}

7. Add a rule to the checkout complete event that has an action of "Adjust contribution amount."
{ "rules_update_campaign_current" : {
    "LABEL" : "Update Campaign Current",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "donation" ],
    "REQUIRES" : [
      "commerce_order",
      "field_collection_contributions",
      "commerce_checkout"
    ],
    "ON" : [ "commerce_checkout_complete" ],
    "IF" : [
      { "commerce_order_contains_product_type" : {
          "commerce_order" : [ "commerce_order" ],
          "product_type" : { "value" : { "product" : "product" } },
          "operator" : "\u003E=",
          "value" : "1"
        }
      }
    ],
    "DO" : [
      { "commerce_checkout_contribution" : { "commerce_order" : [ "commerce_order" ] } }
    ]
  }
}
