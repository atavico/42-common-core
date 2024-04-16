from django import forms
from django.contrib.auth.forms import UserCreationForm, UserChangeForm
from .models import User


class LoginForm(forms.Form):
    email = forms.CharField(max_length=65)
    password = forms.CharField(max_length=65, widget=forms.PasswordInput)


class CustomUserCreationForm(UserCreationForm):
    class Meta(UserCreationForm.Meta):
        model = User
        fields = ('email', 'password1', 'password2')


class RegisterForm(CustomUserCreationForm):

    class Meta:
        model = User
        fields = ['email', 'password1', 'password2']


class UserChangeForm(UserChangeForm):

    class Meta:
        model = User
        fields = ('email', )