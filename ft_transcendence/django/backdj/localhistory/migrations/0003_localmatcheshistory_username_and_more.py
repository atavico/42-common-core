# Generated by Django 4.2.7 on 2024-03-27 22:05

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('localhistory', '0002_alter_localmatcheshistory_tournament_stage'),
    ]

    operations = [
        migrations.AddField(
            model_name='localmatcheshistory',
            name='username',
            field=models.CharField(default='', max_length=8),
        ),
        migrations.AddField(
            model_name='localtournamentshistory',
            name='username',
            field=models.CharField(default='', max_length=8),
        ),
        migrations.AlterField(
            model_name='localtournamentshistory',
            name='second',
            field=models.CharField(default='', max_length=8),
        ),
        migrations.AlterField(
            model_name='localtournamentshistory',
            name='winner',
            field=models.CharField(default='', max_length=8),
        ),
    ]
