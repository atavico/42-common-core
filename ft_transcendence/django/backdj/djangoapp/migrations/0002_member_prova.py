# Generated by Django 4.2.7 on 2024-01-04 11:23

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('djangoapp', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='member',
            name='prova',
            field=models.CharField(default=None, max_length=255),
            preserve_default=False,
        ),
    ]
