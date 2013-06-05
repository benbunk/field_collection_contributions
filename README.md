field_collection_contributions
==============================

A field collection formatter for contributions. To replace commerce_contributions module.

Setup
==============================

1. Create a new field collection on the product variation type.

2. Add two fields to the collection
    1. Donation Current - field_donation_current - decimal
    2. Donation Goal - field_donation_goal - decimal

3. Change the display of the field_collection on the product variation to Contribution Meter.
Configure this formatter and set the Donation Current to the current value, set Donation Goal to the
goal value.

4. Add a field called field_donation_amount on the product line item.

5. Add a rule to add the field_donation_amount to the line item unit price.

6. Add a rule to the checkout complete event that has an action of "Adjust contribution amount."
